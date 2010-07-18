# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to, avoiding a bug in XCode 1.5
all.Debug: \
	/Users/NK/Development/factions/build/bin/Debug/Application\
	/Users/NK/Development/factions/build/bin/Debug/libBase.dylib

all.Release: \
	/Users/NK/Development/factions/build/bin/Release/Application\
	/Users/NK/Development/factions/build/bin/Release/libBase.dylib

all.MinSizeRel: \
	/Users/NK/Development/factions/build/bin/MinSizeRel/Application\
	/Users/NK/Development/factions/build/bin/MinSizeRel/libBase.dylib

all.RelWithDebInfo: \
	/Users/NK/Development/factions/build/bin/RelWithDebInfo/Application\
	/Users/NK/Development/factions/build/bin/RelWithDebInfo/libBase.dylib

# For each target create a dummy rule so the target does not have to exist
/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib:
/Users/NK/Development/factions/build/bin/Debug/libBase.dylib:
/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib:
/Users/NK/Development/factions/build/bin/MinSizeRel/libBase.dylib:
/Users/NK/Development/factions/build/bin/RelWithDebInfo/libBase.dylib:
/Users/NK/Development/factions/build/bin/Release/libBase.dylib:


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
/Users/NK/Development/factions/build/bin/Debug/Application:\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/factions/build/bin/Debug/libBase.dylib\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib
	/bin/rm -f /Users/NK/Development/factions/build/bin/Debug/Application


/Users/NK/Development/factions/build/bin/Debug/libBase.dylib:\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib
	/bin/rm -f /Users/NK/Development/factions/build/bin/Debug/libBase.dylib


/Users/NK/Development/factions/build/bin/Release/Application:\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/factions/build/bin/Release/libBase.dylib\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib
	/bin/rm -f /Users/NK/Development/factions/build/bin/Release/Application


/Users/NK/Development/factions/build/bin/Release/libBase.dylib:\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib
	/bin/rm -f /Users/NK/Development/factions/build/bin/Release/libBase.dylib


/Users/NK/Development/factions/build/bin/MinSizeRel/Application:\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/factions/build/bin/MinSizeRel/libBase.dylib\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib
	/bin/rm -f /Users/NK/Development/factions/build/bin/MinSizeRel/Application


/Users/NK/Development/factions/build/bin/MinSizeRel/libBase.dylib:\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib
	/bin/rm -f /Users/NK/Development/factions/build/bin/MinSizeRel/libBase.dylib


/Users/NK/Development/factions/build/bin/RelWithDebInfo/Application:\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/factions/build/bin/RelWithDebInfo/libBase.dylib\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib
	/bin/rm -f /Users/NK/Development/factions/build/bin/RelWithDebInfo/Application


/Users/NK/Development/factions/build/bin/RelWithDebInfo/libBase.dylib:\
	/Users/NK/Development/factions/etc/vendor/physfs/libphysfs.dylib\
	/Users/NK/Development/boost-trunk/stage/lib/libboost_filesystem.dylib
	/bin/rm -f /Users/NK/Development/factions/build/bin/RelWithDebInfo/libBase.dylib


