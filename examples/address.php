<?php
require dirname(__FILE__) . DIRECTORY_SEPARATOR . "common.php";
require dirname(dirname(__FILE__)) . DIRECTORY_SEPARATOR . "tests/Message/Base.php";
require dirname(dirname(__FILE__)) . DIRECTORY_SEPARATOR . "tests/Message/User.php";
require dirname(dirname(__FILE__)) . DIRECTORY_SEPARATOR . "tests/Message/Addressbook.php";

$u = new User();
$u->setId(20);
$u->setOffense(105);
$u->setName("chobie");

$u2 = new User();
$u2->setId(21);
$u2->setOffense(108);

$u2->setName("charmy");

$addr = new AddressBook();
$addr->addUser($u);
$addr->addUser($u2);

$data = ProtocolBuffers::encode($u2->getProto(), $u2);
//echo $data;

//$data = ProtocolBuffers::encode($addr->getProto(), $addr);
ProtocolBuffers::decode($u2->getProto(), "User", $data);
$end= microtime(true);

//var_dump(AddressBook::unserialize($data));
//echo ProtocolBuffers::generateProto("User");
//echo ProtocolBuffers::generateProto("AddressBook");
