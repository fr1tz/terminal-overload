//------------------------------------------------------------------------------
// Alux Ethernet Prototype
// Copyright notices are in the file named COPYING.
//------------------------------------------------------------------------------

datablock AudioProfile(WpnParrotMinigunSpinUpSound)
{
	filename = "content/rotc/p.5.3/sounds/rotc/spin2up.wav";
	description = AudioDefault3D;
	preload = true;
};

datablock AudioProfile(WpnParrotMinigunSpinDownSound)
{
	filename = "content/rotc/p.5.3/sounds/rotc/spin2down.wav";
	description = AudioDefault3D;
	preload = true;
};

datablock AudioProfile(WpnParrotMinigunSpinSound)
{
	filename = "content/rotc/p.5.3/sounds/rotc/spin2.wav";
	description = AudioDefaultLooping3D;
	preload = true;
};

datablock AudioProfile(WpnParrotMinigunFireSound)
{
	filename = "content/rotc/p.5.3/sounds/rotc/spin2fire.wav";
	description = AudioDefaultLooping3D;
	preload = true;
};

datablock AudioProfile(WpnParrotMinigunProjectileImpactSound)
{
	filename = "content/rotc/p.5.3/sounds/rotc/impact1.wav";
	description = AudioDefault3D;
	preload = true;
};

datablock AudioProfile(WpnParrotMinigunProjectileFlybySound)
{
	filename = "content/rotc/p.5.3/sounds/rotc/flyby1.wav";
	description = AudioCloseLooping3D;
	preload = true;
};

datablock AudioProfile(WpnParrotMinigunProjectileMissedEnemySound)
{
	filename = "content/rotc/p.5.3/sounds/rotc/ricochet1-1.wav";
	alternate[0] = "content/rotc/p.5.3/sounds/rotc/ricochet1-1.wav";
	alternate[1] = "content/rotc/p.5.3/sounds/rotc/ricochet1-2.wav";
	alternate[2] = "content/rotc/p.5.3/sounds/rotc/ricochet1-3.wav";
	alternate[3] = "content/rotc/p.5.3/sounds/rotc/ricochet1-4.wav";
	alternate[4] = "content/rotc/p.5.3/sounds/rotc/ricochet1-5.wav";
	alternate[5] = "content/rotc/p.5.3/sounds/rotc/ricochet1-6.wav";
	description = AudioClose3D;
	preload = true;
};


