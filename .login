# The n option on mesg below says you're refusing write(1)
# messages.  We put this here to safeguard you against bad apples who
# might use the write program to send character streams that control
# your terminal against your wishes.  Remove "mesg n" at your own risk.

mesg n

alias logo logout
set ignoreeof
set mail=(5 /usr/spool/mail/$USER /var/mail/$USER )
#
# Give TERM a value just if this in not automatically assigned
if (`printenv TERM` == "" ) then
	setenv TERM vt100
endif
#
# let's get our termcap set right
#
switch ($TERM)
    case xterms:
    case xterm:
    case tvi950:
	breaksw
    case dialup:
# Your terminal type at home goes here    
#	setenv TERM tvi950
#	breaksw
    default:    
	setenv TERM vt100
	echo -n "Terminal type? ($TERM) "
        if ( ! ${?DT} ) then
		set newterm = $<
		if (x$newterm != x) setenv TERM $newterm
	endif
endsw
set nonomatch
eval `tset -Q -s $TERM`
unset nonomatch
echo Terminal type is $TERM
if ( `uname` == "SunOS") then
  /usr/ucb/stty dec 
  msgs -q
endif
