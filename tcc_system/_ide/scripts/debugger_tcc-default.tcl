# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\hdl-projects\gyro_test\test_system\_ide\scripts\debugger_test-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\hdl-projects\gyro_test\test_system\_ide\scripts\debugger_test-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent Arty S7 - 50 210352B84088A" && level==0 && jtag_device_ctx=="jsn-Arty S7 - 50-210352B84088A-0362f093-0"}
fpga -file C:/hdl-projects/gyro_test/test/_ide/bitstream/baremetal_wrapper.bit
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
loadhw -hw C:/hdl-projects/gyro_test/baremetal_wrapper/export/baremetal_wrapper/hw/baremetal_wrapper.xsa -regs
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow C:/hdl-projects/gyro_test/test/Debug/test.elf
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
con
