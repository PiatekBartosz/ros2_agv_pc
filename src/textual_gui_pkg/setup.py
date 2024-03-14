from setuptools import find_packages, setup

package_name = 'textual_gui_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='root',
    maintainer_email='maksgrabowy@gmail.com',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'tui_serial = textual_gui_pkg.tui_serial:main',
            'tui_2 = textual_gui_pkg.tui_2:main',
            'tui_topic = textual_gui_pkg.tui_topic:main'
        ],
    },
)
