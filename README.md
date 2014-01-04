<h1>Particle System demo</h1>
<p>Colin Ledbetter</p>
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
<li>Pressing 'q' will exit the program</li>
<li>Pressing 'l' will toggle lines being drawn between frames, instead of just 
singular points.</li>
<li>Pressing 'c' will toggle clearing the renderer between frames.</li>
<li>Pressing 'd' will dump the memory used by the particles.  This causes performance
to increase, but all existing particles will perish.  This will also clear the screen.  
It is HIGHLY RECOMMENDED to enable clearing of the screen before dumping.</li>
<li>Pressing 'k' will toggle automatic particle destruction.  If enabled, particles
will die after a set amount of frames.</li>
<li>Pressing certain numbers will change the types of colors that particles will appear as.
<ul>
<li>0 - Rainbow (Default)</li>
<li>1 - Grayscale</li>
<li>2 - Redscale</li>
<li>3 - Greenscale</li>
<li>4 - Bluescale</li>
</ul></li>
</ul>

<h2>Purpose</h2>
<p>The reason for making this was mostly as a learning experience.  It can also 
be used as a base in other graphics-related programs that might use similar 
features.  For example, sprites can be implemented as an extension of the 
Particle class, using surfaces or textures instead of individual pixel colors.  
Feel free to use this without any credit to me.</p>

<h2>Plans for future development</h2>
<p>I plan on implementing sprites and images, and I will continue to use SDL2 in 
doing so.</p>