#!/usr/addons/powdertoy/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/", "include/powder_toy", "include/json"])
env.Append(CXXFLAGS=["-fexceptions"])  # Enable exception handling
sources = Glob("src/*.cpp")

# Add the path to the Powder Toy library
env.Append(LIBPATH=[os.path.join(os.getcwd(), "lib")])

# Specify the Powder Toy library to link
env.Append(LIBS=["powder"])

LIB_NAME = "powder_toy_godot"
PROJECT_NAME = "powder_toy_demo"

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{}/addons/powdertoy/lib{}.{}.{}.framework/lib{}.{}.{}".format(
            PROJECT_NAME, LIB_NAME, env["platform"], env["target"], LIB_NAME, env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "{}/addons/powdertoy/lib{}.{}.{}.simulator.a".format(PROJECT_NAME, LIB_NAME, env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "{}/addons/powdertoy/lib{}.{}.{}.a".format(PROJECT_NAME, LIB_NAME, env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "{}/addons/powdertoy/lib{}{}{}".format(PROJECT_NAME, LIB_NAME, env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
