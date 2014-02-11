//------------------------------------------------------------------------------
// Revenge Of The Cats: Ethernet
// Copyright notices are in the file named COPYING.
//------------------------------------------------------------------------------

datablock TSShapeConstructor(RedStandardCatDts)
{
	baseShape = "./player2.red.dts";
	sequenceBaseDir = "./../a/";
	
	// movement when standing...
	sequence0  = "tl/root.dsq root";
	sequence1  = "nm/run.dsq run";
	sequence2  = "nm/back.dsq back";
	sequence3  = "nm/side.dsq side";
	
	// movement when marching...
	sequence4  = "tl/root.dsq rootMarching";
	sequence5  = "nm/run.dsq runMarching";
	sequence6  = "nm/back.dsq backMarching";
	sequence7  = "nm/side.dsq sideMarching";
	
	// movement when crouched...
	sequence8  = "tl/rootcrouched.dsq rootCrouched";
	sequence9  = "nm/run.dsq runCrouched";
	sequence10  = "nm/back.dsq backCrouched";
	sequence11  = "nm/side.dsq sideCrouched";
	
	// movement when prone...
	sequence12 = "fb/rootprone.dsq rootProne";
	sequence13 = "fb/rootprone.dsq rootProne";
	sequence14 = "fb/rootprone.dsq rootProne";
	sequence15 = "fb/rootprone.dsq rootProne";
	
	// arm threads...
	sequence16 = "a/holdnoweapon.dsq look";
	sequence17 = "a/discdeflect_left_base.dsq discdeflect_left_base";
	sequence18 = "a/holdgun_onehand.dsq look2";
	sequence52 = "a/holdblaster.dsq holdblaster";
	sequence53 = "ub/aimblaster.dsq aimblaster";
	sequence19 = "ub/holdrifle.dsq holdrifle";
	sequence51 = "ub/aimrifle.dsq aimrifle";
	sequence20 = "ub/holdshield.dsq holdshield";
	sequence46 = "a/holdspear.dsq holdspear";
	sequence47 = "a/holdaimspear.dsq holdaimspear";

	// other...
	sequence21 = "nm/diehead.dsq death1";
	sequence22 = "nm/diechest.dsq death2";
	sequence23 = "nm/dieback.dsq death3";
	sequence24 = "nm/diesidelf.dsq death4";
	sequence25 = "nm/diesidert.dsq death5";
	sequence26 = "nm/dieleglf.dsq death6";
	sequence27 = "nm/dielegrt.dsq death7";
	sequence28 = "nm/dieslump.dsq death8";
	sequence29 = "nm/dieknees.dsq death9";
	sequence30 = "nm/dieforward.dsq death10";
	sequence31 = "nm/diespin.dsq death11";

	sequence32 = "nm/headside.dsq headside";
	sequence33 = "nm/recoilde.dsq light_recoil";
	sequence34 = "nm/sitting.dsq sitting";
	sequence35 = "fb/cel_headbang.dsq celsalute";
	sequence36 = "nm/tauntbest.dsq celwave";
	sequence37 = "nm/standjump.dsq standjump";

	sequence38 = "nm/head.dsq head";
	sequence39 = "nm/fall.dsq fall";
	sequence40 = "nm/land.dsq land";
	sequence41 = "nm/jump.dsq jump";
	
	sequence42 = "fb/cel_hail.dsq celhail";
	
	sequence43 = "ub/throwsidearm.dsq throwSidearm";
	sequence44 = "ub/firearmcannon.dsq fireArmcannon";
	sequence48 = "ub/aimspear.dsq aimSpear";
	sequence49 = "ub/throwSpear.dsq throwSpear";
	sequence50 = "ub/discdeflect_left_anim.dsq discdeflect_left_anim";
	sequence54 = "ub/throwinterceptor.dsq throwInterceptor";
	
	sequence45 = "fb/flyer.dsq flyer";
	
	sequence55  = "b/slide.dsq slide";	
};

datablock TSShapeConstructor(BlueStandardCatDts : RedStandardCatDts)
{
	baseShape = "./player2.blue.dts";
};
