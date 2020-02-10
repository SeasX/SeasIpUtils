<?php
/**
 * @author ciogao@gmail.com
 * Date: 2020/1/22 10:23 AM
 */

$sIpUtils = new SeasIpUtils();

$result = $sIpUtils->pingExecute("-n -c 10 -i 0.3 -s 32 -W 10 www.sina.com");
var_dump($result);

$result = $sIpUtils->pingExecute("-n -c 10 -i 0.3 -s 32 -W 10 www.baidu.com");
var_dump($result);

$result = $sIpUtils->pingExecute("-n -c 10 -i 0.3 -s 32 -W 10 www.cloudwise.com");
var_dump($result);
