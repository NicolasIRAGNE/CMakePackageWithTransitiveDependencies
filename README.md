## CMakeTransitiveDeps

### Edit: nlohmann_json has been added after for demonstration, but it uses the same method as LibA. 

This repository was created to test transitive dependencies with CMakem, and identify what needs to be done on individual targets.

The situation is as follows:

![image](https://user-images.githubusercontent.com/16356420/145047079-a1ec8f21-e59f-4e6b-8db1-d31d9e29025e.png)

Our main project here is MainExe. It depends on LibB.
LibB is publicly linked to LibA.

MainExe does not explicitly use LibA, so we do not want to have to manually link it.

In order to make it so MainExe needs only to link with LibB and work out of the box, we will need several things.

 - First, we need to properly export LibB's targets, and have every property set correctly. It needs to publicly link to LibA. Then, we create a LibBConfig.cmake using CMakePackageHelpers.
 - Now we can use Find_Package(LibB) and it successfully finds LibB. However, it will still complain about needing to link to LibA. This is because LibA's targets need to be exported as well.
 - So now we need to export LibA's targets, the same way we exported LibB.
 - Inside LibB's config file, we add the following:
```CMake
list(APPEND CMAKE_PREFIX_PATH @PACKAGE_CMAKE_INSTALL_LIBDIR@/cmake/LibA)
include(CMakeFindDependencyMacro)
find_dependency(LibA REQUIRED)
```
 - Now we need to make sure that LibA implements an install method, and that we add the path to the generated config file correctly. This way, when processing LibBConfig.cmake, cmake will look for LibA's config file, that should be inside the install tree.

So, in summary:
 - It IS possible to handle transitive dependencies with CMake.
 - We just need to make sure that every dependency provides a way to export its targets.
 - Depending on the method used, make sure that the dependency either generates a config file or provides a find module. Alternatively, write your own and install it (I would recommend **NOT** doing this and instead use the same method for the main file)
 - We need to explicitly add them to the config file of the target that publicly links to it.
