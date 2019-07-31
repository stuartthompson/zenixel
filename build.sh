#!/bin/bash

PLATFORM=$1
TASK=$2
INSTALLDIR=$3

# Validate arguments
if [ "$PLATFORM" != "linux" ] && [ "$PLATFORM" != "osx" ]; then
    echo "Usage: sh ./build.sh [platform]"
    exit 0
fi
if [ "$TASK" == "install" ] && [ "$INSTALLDIR" == "" ]; then
    echo "Install dir must be specified when task is install."
    exit 0
fi

# Base-config
INC="-I./inc -I./inc/math -I./inc/render"
INCDIR=./inc
SRCROOT=./src
SRCDIRS=(math render)
BUILDDIR=./build
DISTDIR=./dist
OBJDIR=$BUILDDIR/obj
LIBDIR=$BUILDDIR/lib
OUTPUT=libzenixel.a
CFLAGS="-std=c++17"

# Set platform-specific variables
if [ "$PLATFORM" == "linux" ]; then
    echo "Targeting Linux"
    PLATFORM="linux"
    INC="$INC -I/usr/include/SDL2"
    CFLAGS="-D_REENTRANT" $CFLAGS
fi
if [ "$PLATFORM" == "osx" ]; then
    echo "Targeting OSX"
    PLATFORM="osx"
    INC="$INC -I/usr/local/include/SDL2"
    CFLAGS="-D_THREAD_SAFE" $CFLAGS
fi

if [ "$TASK" == "clean" ] || [ "$TASK" == "" ]; then
    # Clean up previous build
    echo "Cleaning build output"
    rm -rf build                                                # Remove build folder
    rm -rf dist                                                 # Remove distribution folder
fi

if [ "$TASK" == "build" ] || [ "$TASK" == "" ]; then
    # Create output directories
    echo "Creating build folders"
    mkdir $BUILDDIR                                             # Create build folder
    mkdir $OBJDIR                                               # Create obj folder
    mkdir $LIBDIR                                               # Create lib folder
    echo "Creating dist folder"
    mkdir $DISTDIR                                              # Create distribution folder

    # Compile object files
    echo "Compiling object files"
    OBJFILES=""
    for SRCDIR in ${SRCDIRS[@]}
    do
        echo "Compiling src in" $SRCROOT/$SRCDIR
        for SRC in $SRCROOT/$SRCDIR/*.cpp                       # Iterate source files
        do
            OBJF=$(basename "$SRC")                             # Get just the file name (strip path)
            OBJFNE="${OBJF%.*}"                                 # Get obj file name without .cpp ext
            OBJ=$OBJFNE.o                                       # Create obj file name with .o extension
            echo "Compiling" $SRC "=>" $OBJDIR/$OBJ
            g++ -c $SRC $INC -o $OBJDIR/$OBJ $CFLAGS            # Compile object file
            OBJFILES=$OBJFILES" "$OBJDIR/$OBJ                   # Concatenate to list of obj files
        done
    done

    # Compile library
    echo "Linking" $LIBDIR/$OUTPUT "from" $OBJFILES
    ar -rcs $LIBDIR/$OUTPUT $OBJFILES                            # Compile static library

    # Copy output to dist folder
    echo "Copying files to distribution folder"
    cp -r $INCDIR $DISTDIR
    cp -r $LIBDIR $DISTDIR
fi

if [ "$TASK" == "install" ] && [ "$INSTALLDIR" != "" ]; then
    # Remove previous install
    echo "Removing previous install directories"
    rm -rf $INSTALLDIR/inc/zenixel
    rm -rf $INSTALLDIR/lib/zenixel 

    # Create install dirs
    echo "Creating installation directories"
    mkdir $INSTALLDIR/inc/zenixel
    mkdir $INSTALLDIR/lib/zenixel

    # Install headers and lib
    echo "Installing zenixel headers to" $INSTALLDIR"/inc/zenixel"
    cp -r $DISTDIR/inc/* $INSTALLDIR/inc/zenixel/
    echo "Installing zenixel library to" $INSTALLDIR"/lib/zenixel"
    cp $DISTDIR/lib/$OUTPUT $INSTALLDIR/lib/zenixel/

    echo "To install into /usr folder run: ln -s $INSTALLDIR/lib/zenixel /usr/local/lib/zenixel && ln -s $INSTALLDIR/inc/zenixel /usr/local/include/zenixel"
fi