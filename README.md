# Silicon
A basic operating system with emphasis on performance and control of a system
This is a project I have wanted to do, and decided to start. At least for now, this is a hobby, and there are no enforced goals for it. However, we would like to have a terminal, some networking, basic graphics, programs, compiling, and (hopefully) a GUI. 

Building 
Currently this builds fine on linux (arch 5.16.14)
You will need GCC and QEMU to run it, and for WSL it might benefit to change the line 
mkfs.fat -F 32 $(BUILDDIR)/$(OSNAME).img 
to 
mformat -i $(BUILDDIR)/$(OSNAME).img -f 1440 ::
This is not tested however. You have to cd into gnu-efi and run make all and then make bootloader. Then cd into the kernel directory and do make all, then make run to run (might not work in WSL). Untested on Mac
