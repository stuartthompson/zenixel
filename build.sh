INC="-I./inc/math -I./inc/render -I/usr/include/SDL2"
INCDIR=./inc
SRCROOT=./src
SRCDIRS=(math render)
BUILDDIR=./build
DISTDIR=./dist
OBJDIR=$BUILDDIR/obj
LIBDIR=$BUILDDIR/lib
OUTPUT=libzenixel.a
CFLAGS="-D_REENTRANT --std=c++17"

# Clean up previous builds
echo "Cleaning build output"
rm -rf build                                                # Remove build folder
rm -rf dist                                                 # Remove distribution folder

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
ar rcs $LIBDIR/$OUTPUT $OBJFILES                            # Compile static library

# Copy output to dist folder
echo "Copying files to distribution folder"
cp -r $INCDIR $DISTDIR
cp -r $LIBDIR $DISTDIR
