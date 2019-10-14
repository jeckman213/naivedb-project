#---- PATHS -----------------------------------------------------------------

PATH=/usr/local/bin:/usr/bin:/usr/openwin/bin:/usr/dt/bin:\
/usr/local/X11/bin:/usr/ccs/bin:/usr/ucb

if [ `uname` == SunOS ]; then
  MANPATH=/usr/local/man:/usr/man:/usr/openwin/man::/usr/dt/man:\
/usr/local/X11/man:/opt/SUNWspro/man:/usr/local/perl-module/man:\
/usr/share/local/ucbman
  msgs -q
fi

XAPPLRESDIR=/usr/local/X11/lib/X11/app-defaults:/usr/openwin/lib/app-defaults:\
/usr/lib/X11/app-defaults:/usr/local/X11R4/lib/X11/app-defaults

export PATH MANPATH XAPPLRESDIR 

#---- Aliases ---------------------------------------------------------------

alias back='cd -'
alias ll='ls -ls'
alias h='history'
alias j='jobs -l'
alias mak='make -k 2>ERRS &'

alias motd='/bin/cat /etc/motd'
alias term='eval `tset -s -Q `'
alias dir='ls -alsFq | more'
#
set -b 
set -o noclobber

#---- Terminal -------------------------------------------------------------

eval `tset -s ?vt100 -Q`

#case $TERM in 
#    xterms | xterm | tvi950 )	;;
## Your terminal type at home goes here    
##       TERM=tvi950
#    dialup ) ;;
#    * ) TERM=vt100
#        print -n "Terminal type? ($TERM) "
#        if [ ! "$DT" ]; then
#                read newterm
#                if  [ x$newterm != x ]; then
#                    TERM=$newterm
#                fi 
#        fi ;;
#esac

#---- Environment ----------------------------------------------------------

HOSTNAME=$(hostname | cut -d. -f1)
PS1='$HOSTNAME:$PWD>'

EDITOR=emacs
PAGER=less

HISTSIZE=200

export PS1 EDITOR PAGER 

#---- Misc.-----------------------------------------------------------------

mesg n

umask 077

#
# For more information on modifying your shell environment, refer to the 
# man pages on sh and/or ksh.
#
