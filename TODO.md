# Classic Camera Update

Getting camera real time images

Applying modification: 
- Color compression
- Reverse Effect
- Gray shades
- Blur
- Adding textes
- Etc...

Modifying Camera stream data

- Adding Images 
- Playing Video

Optionnal: Play with the Mic aswell:
- forced mute
- voice effects
- Musics

All the camera Part could be done using  OpenCv but if I feel confident enough I may just use V4l2

# Camera default Overriding

The point of this part is to be able to create a virtual Camera which will use the stream taht my programm send in order to be able to use my modified camera as one On call like Teams or discord

To create this I may need to setup a vCamera using `v4l2loopback`