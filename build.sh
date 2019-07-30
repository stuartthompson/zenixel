INC="-I./inc/math -I./inc/render -I/usr/include/SDL2"
SRCROOT=./src
SRCDIRS=(math render)
BUILDDIR=./build
OBJDIR=$BUILDDIR/obj
LIBDIR=$BUILDDIR/lib
OUTPUT=zenlib.a
CFLAGS="-D_REENTRANT --std=c++17"

# Clean up previous builds
echo "Cleaning build output"
rm -rf build                                                # Remove build folder

# Create build output directories
echo "Creating build folders"
mkdir ./build                                               # Create build folder
mkdir ./build/obj                                           # Create obj folder
mkdir ./build/lib                                           # Create lib folder

# Compile object files
echo "Compiling object files"
OBJFILES=""
for SRCDIR in ${SRCDIRS[@]}
do
    echo "Compiling src in" $SRCROOT/$SRCDIR
    for SRC in $SRCROOT/$SRCDIR/*.cpp                       # Iterate source files
    do
        OBJF=$(basename "$SRC")                             # Get just the file name (strip path)
        OBJFNE="${OBJF%.*}"                                  # Get obj file name without .cpp ext
        OBJ=$OBJFNE.o                                       # Create obj file name with .o extension
        echo "Compiling" $SRC "=>" $OBJDIR/$OBJ
        g++ -c $SRC $INC -o $OBJDIR/$OBJ $CFLAGS  # Compile object file
        OBJFILES=$OBJFILES" "$OBJDIR/$OBJ                   # Concatenate to list of obj files
    done
done

# Compile library
echo "Linking" $LIBDIR/$OUTPUT "from" $OBJFILES
ar rcs $LIBDIR/$OUTPUT $OBJFILES                            # Compile static library