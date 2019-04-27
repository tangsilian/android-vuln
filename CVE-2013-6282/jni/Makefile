
all: install

build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk APP_PLATFORM=android-16 APP_ABI=armeabi

push: build
	adb push libs/armeabi/exploit /data/local/tmp/exploit

root: push
	adb shell 'chmod 777 /data/local/tmp/exploit'
	adb shell '/data/local/tmp/exploit'

clean:
	rm -rf libs
	rm -rf obj

