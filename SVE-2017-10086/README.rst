=====
MTPwn
=====

* *Author:* Salvatore Mesoraca (https://smeso.it)
* *IDs:* **SVE-2017-10086**
* *Severity:* **High**
* *Affected versions:* KK(4.4.x), L(5.x), M(6.x), N(7.x)
* *Date of discovery:* 25/08/2017
* *Date of upstream report:* 28/08/2017
* *Date of fix:* 27/10/2017
* *Date of public disclosure:* 02/01/2018

What's MTPwn?
*************
**MTPwn** is a PoC exploit for a vulnerability of Samsung's Android phones that
allows an attacker to access phone storages via USB, bypassing lock screen
and/or *Charge only* mode.
This program will list path and names of files on a device (both internal
memory and external SD) and will download one random file in the current
directory.
It will also create a file named *PWND* in the root of one of the device's
storages.
The main goals of this program are to demonstrate the vulnerability and to
allow people to test their own device for it, it doesn't aim to provide a
ready to use exploit for people willing to do harm.
Nevertheless MTPwn can be easily modified to download or delete any file,
to create and delete folders and to do many other things.

Currently known affected devices
********************************
Any Samsung Android device that lacks **SMR-OCT-2017** or **SMR-NOV-2017**
update. The exact update that fixes this issue depends on the device model.

How it works
************
One of the most common ways to connect your Android phone to your computer is
by using the Media Transfer Protocol (MTP).
Via MTP you can manage folders, files (and some other things) on the different
storages (i.e. internal memory and SD) available on your device.
When the screen of the phone is locked with password or when the USB mode is
set to *Charge only* it shouldn't be possible to access the device via MTP
(or other USB protocols).
Unfortunately what really happens is that the device will prevent you  from
obtaining the list of the available storages, but it will let you do everything
else.
Many common MTP clients won't, probably, let you access a device that reports
zero storages. But you can write a client that just asks for a list of all
files on all storages and the device will satisfy your request.
The interesting thing is that in the answer that you will get from the device
you will also have storage ids for the returned files, which means that now
you can use those storage ids with request that can't be issued generically
against *all storages* i.e. file uploads.
According to my experiments this vulnerability is present on a great variety
of Samsung's devices from 2012 until 2017, with any android versions from 4.0.3
to 7.x.

How to test your device
***********************
First of all install `libmtp`:

* Debian/Ubuntu::

	sudo apt-get install libmtp-dev

Download the latest MTPwn sources::

	curl -L "https://github.com/smeso/MTPwn/archive/v0.1.tar.gz" -o mtpwn.tgz

Optionally, verify the sources against `0xD7286260BBF31719A2759FA485F0580B9DACBE6E`::

	curl -L \
	"https://github.com/smeso/MTPwn/releases/download/v0.1/v0.1.tar.gz.asc" \
	-o mtpwn.tgz.asc
	gpg -v --verify mtpwn.tgz.asc

Extract and compile the sources::

	tar xzvf mtpwn.tgz
	cd MTPwn-0.1
	make

Connect your device (with the screen locked with password) and run MTPwn::

	./mtpwn

On some devices it can take a long time, just waits until it returns.
Please make sure that there isn't any other application trying to use MTP.
If it fails try disconnecting and reconnecting the device and run MTPwn again
a couple of times.
If it works it should show you a list of all files available via MTP,
you should find the file got from the device in your current directory and
a file named PWND in the root of one of your device's storages.

License
*******
This code is released under `GPL-3`.
