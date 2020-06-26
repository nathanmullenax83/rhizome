# rhizome
## What is Rhizome?
Rhizome is a multi-purpose library written in C++. It is geared toward creating an open
social networking platform where everyone has their own server, fine grained control over 
content sharing, and if need be, easy implementation of custom parsing tools. 

Rhizome is experimental. In addition to producing a library which can be linked and used in other programs, it produces an executable which attempts to showcase functionality which is more or less
complete. In this sense, it is also a 'disc magazine.' 

## What else can you do with this library?
Though still a work in progress, repl_demo.cpp shows how an interpreter for a context free language can be constructed with the rhizome::lexer and rhizome::parser sub-libraries. These will probably be split into a separate, less 'kitchen sink' kind of project.

There's also some unicode terminal IO stuff, assuming your terminal can render it. The disc magazine binary assumes your terminal is capable of rendering unicode output. All of that is in the rhizome::ui namespace.





