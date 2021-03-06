
# wireless7.tcl

# create simulator instance
set ns   [new Simulator]

# set up for hierarchical routing
$ns node-config -addressType hierarchical

AddrParams set domain_num_ 3           ;# number of domains
lappend cluster_num 2 1 1              ;# number of clusters in each domain
AddrParams set cluster_num_ $cluster_num
lappend llevel 1 1 2 1            ;# number of nodes in each cluster 
AddrParams set nodes_num_ $llevel ;# of each domain

set tracefd  [open lab7.tr w]
set namtrace [open lab7.nam w]
$ns trace-all $tracefd
$ns namtrace-all-wireless $namtrace 250 250


#Finish Procedure
proc finish {} {
    global ns tracefd namtrace
    close $tracefd
    close $namtrace
        exec nam lab7.nam &

# following code is optional if you use awk script to show the throughput  lab7.awk

	puts "The number of data packets sent "
	exec grep "^+" lab7.tr | grep "tcp" | cut -d " " -f 3 | grep -c "0" &
	puts "The number of packets received at mobile nodes "
	exec grep "^r" lab7.tr | grep "tcp" | grep -c "_4_ AGT" &
	exit 0
}

# Create topography object
set topo   [new Topography]

# define topology
$topo load_flatgrid 250 250

# create God 3 for HA , FA and MH
create-god 3


# hierarchical addresses 
set temp {0.0.0 0.1.0} 

#create wired nodes
 set W0 [$ns node [lindex $temp 0]]
 set W1 [$ns node [lindex $temp 1]]



# Configure for ForeignAgent and HomeAgent nodes
$ns node-config -mobileIP ON \
                 -adhocRouting DSDV \
                 -llType  LL \
                 -macType Mac/802_11  \
                 -ifqType Queue/DropTail/PriQueue  \
                 -ifqLen 50 \
                 -antType  Antenna/OmniAntenna \
                 -propType Propagation/TwoRayGround \
                 -phyType Phy/WirelessPhy \
                 -channelType Channel/WirelessChannel \
		 -topoInstance $topo \
                 -wiredRouting ON \
		 -agentTrace ON \
                 -routerTrace OFF \
                 -macTrace OFF 

# Create HA and FA
set HA [$ns node 1.0.0]
set FA [$ns node 2.0.0]
$HA random-motion 0
$FA random-motion 0

# Position (fixed) for base-station nodes (HA & FA).
$HA set X_ 1.0
$HA set Y_ 2.0
$HA set Z_ 0.0

$FA set X_ 250.0
$FA set Y_ 200.0
$FA set Z_ 0.0

# create a mobilenode that would be moving between HA and FA.
# note address of MH indicates its in the same domain as HA.
$ns node-config -wiredRouting OFF

set MH [$ns node 1.0.1]
set node0 $MH
set HAaddress [AddrParams addr2id [$HA node-addr]]
[$MH set regagent_] set home_agent_ $HAaddress

# movement of the MH
$MH set Z_ 0.0
$MH set Y_ 2.0
$MH set X_ 2.0

# MH starts to move towards FA
$ns at 100.0 "$MH setdest 240.0 210.0 20.0"
# goes back to HA
$ns at 200.0 "$MH setdest 2.0 2.0 20.0"

# create links between wired and BaseStation nodes
$ns duplex-link $W0 $W1 5Mb 2ms DropTail
$ns duplex-link $W1 $HA 5Mb 2ms DropTail
$ns duplex-link $W1 $FA 5Mb 2ms DropTail

$ns duplex-link-op $W0 $W1 orient down
$ns duplex-link-op $W1 $HA orient left-down
$ns duplex-link-op $W1 $FA orient right-down

# setup TCP connections between a wired node and the MobileHost

set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
set sink1 [new Agent/TCPSink]
$ns attach-agent $W0 $tcp1
$ns attach-agent $MH $sink1
$ns connect $tcp1 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
    

$ns initial_node_pos $node0 20

$ns at 100.0 "$ftp1 start"
$ns at 200.0 "$node0 reset"

$ns at 200.0 "$HA reset";
$ns at 200.0 "$FA reset";

$ns at 201.0 "finish"

$ns run



