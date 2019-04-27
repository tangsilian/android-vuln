
all: build

build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk APP_ABI=armeabi

push: build
	adb push libs/armeabi/debugexploit /data/local/tmp/futex

run: push
	adb shell "/data/local/tmp/futex 0 2 0 0"

clean:
	rm -rf libs
	rm -rf obj

