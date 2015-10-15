import sys
import os

TEST_TARGET = "test"

colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

#If the output is not a terminal, remove the colors
if not sys.stdout.isatty():
   for key, value in colors.iteritems():
      colors[key] = ''

compile_source_message = '%sCompiling %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

compile_shared_source_message = '%sCompiling shared %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

link_program_message = '%sLinking Program %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_library_message = '%sLinking Static Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

ranlib_library_message = '%sRanlib Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_shared_library_message = '%sLinking Shared Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])


env = Environment(
  CXXCOMSTR = compile_source_message,
  CCCOMSTR = compile_source_message,
  SHCCCOMSTR = compile_shared_source_message,
  SHCXXCOMSTR = compile_shared_source_message,
  ARCOMSTR = link_library_message,
  RANLIBCOMSTR = ranlib_library_message,
  SHLINKCOMSTR = link_shared_library_message,
  LINKCOMSTR = link_program_message,
)
env.VariantDir('build', 'src')

env.Append(CCFLAGS=[
    '-Wall',
    '-Werror',
    '-fcolor-diagnostics',
    '-I/usr/local/include/luajit-2.0/',
    '-I/usr/local/include/',
])
env.Append(LIBPATH=['/usr/local/lib/'])
env.Append(LINKFLAGS=[
    '-lSDL2',
    '-lSDL2_image',
    '-framework', 'OpenGL',
    '-framework', 'Cocoa',
    '-Bstatic', '-lluajit-5.1',
    '-Bdynamic', '-lm', '-ldl',
    '-pagezero_size', '10000',
    '-image_base', '100000000',
    '-lchipmunk'
])

sources = env.Glob('build/*.c')
sources += env.Glob('build/components/*.c')

if TEST_TARGET in COMMAND_LINE_TARGETS:
    env.Append(CPPPATH=["lib/sput-1.3.0"])
    sources += env.Glob("build/test/main.c")
    sources = [s for s in sources if s.path != "build/main.c"]
    tt = env.Program(
        "bin/test-merriment",
        source=sources,
    )
    test_alias = Alias(
        TEST_TARGET,
        [tt],
        tt[0].abspath
    )
else:
    dt = env.Program(
        target="bin/merriment",
        source=sources)
    Default(dt)
