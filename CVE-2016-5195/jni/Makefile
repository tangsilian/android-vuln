
all: build

build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk APP_PLATFORM=android-21

push: build
	adb push libs/armeabi/cowroot /data/local/tmp/cowroot

root: push
	adb shell '/data/local/tmp/cowroot'

clean:
	rm -rf libs
	rm -rf obj

