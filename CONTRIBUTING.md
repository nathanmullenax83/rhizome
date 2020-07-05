Github recommends that projects have guidelines for contributing. I hope other people find this project useful, and I intend to work on it until it is 'production ready'... whatever that means. 

I realize it may be difficult to contribute to a sprawling, amorphous open source project. That said, it shouldn't be too hard to compile if you are on a 'nix based system. There's a makefile I've been maintaining by hand. It has two targets: 'clean' to remove all intermediate binaries, and then 'all' to build the project in situ. 

There are a few dependencies. I've used GMP for arbitrary precision integers, and there are a couple of jpg/png compression libraries linked in, though I think these are going to be moved to some kind of extension so the core project remains portable. 

I use a lot of C++11 features, but not much beyond that. I use GCC with all the warnings turned on, so hopefully other compilers will find my code complaint.

Long story short: I will be extremely pleased if someone manages to compile and use this project on another platform, as I don't have a Windows or Apple machine to develop on. I might try to make a Mono version to make the project more portable. I'm always open to suggestions! Send me an email!
