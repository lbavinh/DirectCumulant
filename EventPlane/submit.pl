#!/usr/bin/perl

print "\nEvent plane calculation from UrQMD 7.7 GeV\n";
$workdir = "/mnt/pool/2/lbavinh/EventPlane";
$runlist = "${workdir}/runlist.list";
open(RUNLIST,"< $runlist") or die "Can not open ${runlist} \n";
while (<RUNLIST>)
{
	$runnum = $_;
	chomp($runnum);

	printf("run = %s\n", $runnum);
	 
	# open file as write_only
	$execfile="${workdir}/tmp/EvPl_${runnum}.sh";
  $outlog="${workdir}/OUT/sum_test_${runnum}_$PBS_JOBID.log";
	open(TASK,"> $execfile") || die "Could not open task (bash) file\n";
	print TASK "#!/bin/bash\n";
  print TASK "#PBS -q medium\n";
  print TASK "#PBS -l nodes=2:ppn=8,walltime=10:00:00\n";
	print TASK "cd ${workdir}\n";
	print TASK "root.exe -b -l -q macro1.C'('${runnum}')' & >> $outlog";
	close TASK;
	chmod(0744,"$execfile");

	# submit job
	system("qsub ${workdir}/tmp/EvPl_${runnum}.sh");

	# to sleep in seconds
	select(undef, undef, undef, 0.1);
}  # end of while runlist
close RUNLIST;