# SeasIpUtils
A IpUtils extension for PHP

## install
```
path/to/phpize
./configure --with-php-config=path/to/php-config
make && make install
```

## test
```
$sIpUtils = new SeasIpUtils();

$result = $sIpUtils->pingExecute("-n -c 10 -i 0.3 -s 32 -W 10 www.baidu.com");
var_dump($result);

```
will get response array
```
array(19) {
  ["hostname"]=>
  string(16) "www.a.shifen.com"
  ["sin_addr"]=>
  string(14) "220.181.38.150"
  ["datalen"]=>
  string(6) "32(60)"
  ["ntransmitted"]=>
  int(10)
  ["nreceived"]=>
  int(10)
  ["nrepeats"]=>
  int(0)
  ["nchecksum"]=>
  int(0)
  ["nerrors"]=>
  int(0)
  ["time_ms"]=>
  int(2995)
  ["packet_loss"]=>
  int(0)
  ["pipesize"]=>
  int(1)
  ["rtt_min_ms"]=>
  string(6) "15.090"
  ["rtt_avg_ms"]=>
  string(6) "16.329"
  ["rtt_max_ms"]=>
  string(6) "18.810"
  ["rtt_mdev_ms"]=>
  string(5) "1.275"
  ["ipg_ms"]=>
  string(1) "0"
  ["ewma_ms"]=>
  string(1) "0"
  ["raw_result_length"]=>
  int(12)
  ["raw_result"]=>
  array(12) {
    [0]=>
    string(60) "PING www.a.shifen.com (220.181.38.150) 32(60) bytes of data."
    [1]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=1 ttl=63 time=16.1 ms"
    [2]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=2 ttl=63 time=16.3 ms"
    [3]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=3 ttl=63 time=15.3 ms"
    [4]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=4 ttl=63 time=16.1 ms"
    [5]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=5 ttl=63 time=15.0 ms"
    [6]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=6 ttl=63 time=15.3 ms"
    [7]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=7 ttl=63 time=18.8 ms"
    [8]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=8 ttl=63 time=15.5 ms"
    [9]=>
    string(60) "40 bytes from 220.181.38.150: icmp_seq=9 ttl=63 time=15.8 ms"
    [10]=>
    string(61) "40 bytes from 220.181.38.150: icmp_seq=10 ttl=63 time=18.6 ms"
    [11]=>
    string(158) "--- www.a.shifen.com ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 2995ms
rtt min/avg/max/mdev = 15.090/16.329/18.810/1.275 ms"
  }
}
```
