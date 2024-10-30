#!/usr/bin/env python
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
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

LIB_NAME = "powder_toy_godot"
PROJECT_NAME = "powder_toy_demo"

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{}/bin/lib{}.{}.{}.framework/lib{}.{}.{}".format(
            PROJECT_NAME, LIB_NAME, env["platform"], env["target"], LIB_NAME, env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "{}/bin/lib{}.{}.{}.simulator.a".format(PROJECT_NAME, LIB_NAME, env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "{}/bin/lib{}.{}.{}.a".format(PROJECT_NAME, LIB_NAME, env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "{}/bin/lib{}{}{}".format(PROJECT_NAME, LIB_NAME, env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
