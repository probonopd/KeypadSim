import os
import shutil
from SCons.Script import ARGUMENTS, DefaultEnvironment

env = DefaultEnvironment()

# Map environment name to example sketch path
example_map = {
    'KeypadController_uno': 'examples/KeypadController/KeypadController.ino',
    'KeypadController_due': 'examples/KeypadController/KeypadController.ino',
    'KeypadController_ColsPulsed_uno': 'examples/KeypadController_ColsPulsed/KeypadController_ColsPulsed.ino',
    'KeypadController_ColsPulsed_due': 'examples/KeypadController_ColsPulsed/KeypadController_ColsPulsed.ino',
    'KeypadSimDemo_uno': 'examples/KeypadSimDemo/KeypadSimDemo.ino',
    'KeypadSimDemo_due': 'examples/KeypadSimDemo/KeypadSimDemo.ino',
    'KeypadSimDemo_ColsPulsed_uno': 'examples/KeypadSimDemo_ColsPulsed/KeypadSimDemo_ColsPulsed.ino',
    'KeypadSimDemo_ColsPulsed_due': 'examples/KeypadSimDemo_ColsPulsed/KeypadSimDemo_ColsPulsed.ino',
}

def before_build(source, target, env):
    envname = env['PIOENV']
    ino_path = example_map.get(envname)
    if ino_path and os.path.isfile(ino_path):
        # Convert .ino to .cpp for PlatformIO
        with open(ino_path, 'r') as f:
            code = f.read()
        main_cpp_path = os.path.join('src', 'main.cpp')
        with open(main_cpp_path, 'w') as f:
            f.write(code)
    else:
        # If not an example env, remove main.cpp if it exists
        main_cpp_path = os.path.join('src', 'main.cpp')
        if os.path.exists(main_cpp_path):
            os.remove(main_cpp_path)

# Register the pre-build action
env.AddPreAction('buildprog', before_build)
