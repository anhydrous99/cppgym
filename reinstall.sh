pip uninstall cppgym
rm -rf build/ cppgym.egg-info/ dist/
python setup.py build
python setup.py install