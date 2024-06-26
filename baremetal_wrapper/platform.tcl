# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\hdl-projects\gyro_test\baremetal_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\hdl-projects\gyro_test\baremetal_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {baremetal_wrapper}\
-hw {C:\hdl-projects\baremetal\baremetal_wrapper.xsa}\
-out {C:/hdl-projects/gyro_test}

platform write
domain create -name {standalone_microblaze_0} -display-name {standalone_microblaze_0} -os {standalone} -proc {microblaze_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {baremetal_wrapper}
platform generate -quick
platform generate
