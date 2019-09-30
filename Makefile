BUILD_DIR=`pwd`/build

CMAKE_TARGET=cmake -S . -B ${BUILD_DIR}

CMAKE_OPTIONS=-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

MAKE_TARGET=make -C ${BUILD_DIR}

FILE_SUFFIXES=-iname *.h -o -iname *.cpp -o -iname *.hpp

FORMAT_TARGET=clang-format -i -sort-includes=false -style=Mozilla

CLEAN=rm -rf ${BUILD_DIR}

CLEAN_ALL=rm -rf ${BUILD_DIR}

UBUNDUT_DEPS=cmake curl libcurl4-gnutls-dev autoconf automake libtool g++ unzip libzmq3-dev xargs

all :: exe compile 

basic :: cmake compile

cmake:
	@${CMAKE_TARGET} ${CMAKE_OPTIONS}

exe:
	@${CMAKE_TARGET} ${CMAKE_OPTIONS} -DBUILD_EXECUTABLE=ON
	@${MAKE_TARGET}

msgs_update:
	@rm -rf ./third_party/sentinet_message_pkg
	@${CMAKE_TARGET} -DCLONE_MSGS=ON
	@${MAKE_TARGET}

compile:
	@${MAKE_TARGET}

clean:
	@${CLEAN}

format ::
	@find ./src ${FILE_SUFFIXES} | xargs ${FORMAT_TARGET}
	@find ./include ${FILE_SUFFIXES} | xargs ${FORMAT_TARGET}

clean-all:
	@${CLEAN_ALL}

install-deps ::
	@sudo apt install ${UBUNDUT_DEPS}

