<h1>Particle System demo</h1>
<p>Colin Ledbetter</p>
<p><img src="http://i.imgur.com/quLzfvo.jpg"/></p>
<h2>Instructions</h2>
<p>Click with the mouse to generate particles of random color.  Each frame with 
the mouse down will create three different particles with random properties.  
The first will have only position and velocity properties, the second will have 
acceleration as well, and finally the third will also have jerk.  The initial 
velocities of all three are the same, and the initial accelerations of the last 
two are the same.  This is to demonstrate how each derivative of position 
affects motion as a whole.  There are also more features of this program, listed 
below:</p>
<ul>
<li>Q - exit the program</li>
<li>L - toggle lines being drawn between frames, instead of just 
singular points. (Default: disabled)</li>
<li>A - toggle drawing antialiased lines. Line drawing must be enabled. (Default: disabled)</li>
<li>C - toggle clearing the renderer between frames. (Default: disabled)</li>
<li>M - toggle the color to clear the screen with between black and white. (Default: black)</li>
<li>D - dump the memory used by the particles.  This causes performance
to increase, but all existing particles will perish.  The screen will not be cleared.</li>
<li>K - toggle automatic particle destruction.  If enabled, particles
will die after a set amount of frames. (Default: enabled)</li>
<li>F - center the cursor on the screen.</li>
<li>B - toggle the blend mode between blending, adding, and replacing. (Default: blending)</li>
<li>Pressing certain numbers will change the types of colors that particles will appear as.
<ul>
<li>0 - Rainbow (Default)</li>
<li>1 - Grayscale</li>
<li>2 - Redscale</li>
<li>3 - Greenscale</li>
<li>4 - Bluescale</li>
<li>5 - Purplescale</li>
<li>6 - Orangescale</li>
<li>7 - Yellowscale</li>
<li>8 - Cyanscale</li>
<li>9 - RGB</li>
</ul></li>
<li>Up/Down - Change the scale of the initial velocity. (Default: 1.0)</li>
<li>Left Control + Up/Down - Change the scale of the initial acceleration. (Default: 1.0)</li>
<li>Left Alt + Up/Down - Change the scale of the initial jerk. (Default: 1.0)</li>
<li>Left/Right - Change the number of packets of particles that are created when
a click occurs. (Default: 1)</li>
<li>Space - toggle automatic particle generation.  This also hides the mouse. (Default: off)</li>
</ul>

<h2>Purpose</h2>
<p>The reason for making this was mostly as a learning experience.  It can also 
be used as a base in other graphics-related programs that might use similar 
features.  For example, sprites can be implemented as an extension of the 
Particle class, using surfaces or textures instead of individual pixel colors.  
Feel free to use this without any credit to me.</p>

<h2>Plans for future development</h2>
<p>I'm currently in the process of considering whether or not to expand this to react to sound input
as a visualizer. I think it would be great for live performances, but it would probably be best if I
cleaned up the source code a significant amount before I undertake that action.</p>
