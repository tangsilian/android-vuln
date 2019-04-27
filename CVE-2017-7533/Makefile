build:
	ndk-build NDK_APPLICATION_MK=Application.mk NDK_PROJECT_PATH=.
push:
	adb push libs/arm64-v8a/main /data/local/tmp/main
	adb shell chmod 0755 /data/local/tmp/main
run:
	adb shell chmod 0755 /data/local/tmp/main
	adb shell /data/local/tmp/main
clean:
	rm -rf obj libs
reboot:
	adb shell reboot
