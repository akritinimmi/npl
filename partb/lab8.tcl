set ns [new Simulator]

set topo [new Topography]
$topo load_flatgrid 500 500

set tf [open lab8.tr w]
$ns trace-all $tf
set nf [open lab8.nam w]
$ns namtrace-all-wireless $nf 500 500

$ns node-config -adhocRouting DSDV \
-llType LL \
-macType Mac/802_11 \
-ifqType Queue/DropTail \
-ifqLen 50 \
-phyType Phy/WirelessPhy \
-channelType Channel/WirelessChannel \
-propType Propagation/TwoRayGround \
-antType Antenna/OmniAntenna \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON


create-god 3

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

#$n0 label "tcp0"
#$n1 label "sink1/tcp1"
#$n2 label "sink2"

#The below code is used to give the initial node positions.
$n0 set X_ 50
$n0 set Y_ 50
$n0 set Z_ 0
$n1 set X_ 100
$n1 set Y_ 100
$n1 set Z_ 0
$n2 set X_ 170
$n2 set Y_ 170
$n2 set Z_ 0

$ns at 0.5 "$n0 setdest 75 50 15"
$ns at 0.5 "$n1 setdest 125 100 25"
$ns at 0.5 "$n2 setdest 150 200 25"

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp0 $sink1


set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
set sink2 [new Agent/TCPSink]
$ns attach-agent $n2 $sink2

$ns connect $tcp1 $sink2

$ns at 5 "$ftp0 start"
$ns at 5 "$ftp1 start"

#The below code is used to provide the node movements.
$ns at 100 "$n1 setdest 150 150 15"
$ns at 190 "$n1 setdest 70 70 15"


proc finish {} {
global ns nf tf
$ns flush-trace
exec nam lab8.nam &
close $tf
exit 0
}
$ns at 250 "finish"
$ns run

