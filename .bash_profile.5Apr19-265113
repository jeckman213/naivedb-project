umask 077
mesg n

PATH=~/bin:/usr/local/bin:/usr/bin:/bin:/usr/openwin/bin:/usr/dt/bin:/usr/local/X11/bin:/usr/ccs/bin:/usr/ucb:.
HISTSIZE=200
HISTFILE=~/.bash_history
HISTCONTROL=ignoredups
set -o noclobber notify ignoreeof

if [ `uname` == SunOS ]; then
  MANPATH=/usr/local/man:/usr/man:/usr/openwin/man:/usr/dt/man:/usr/local/X11/man:/opt/SUNWspro/man:/usr/local/tex/man:/usr/local/perl-module/man:/usr/share/local/ucbman
  msgs -q
fi

PS1="\h% ";
XAPPLRESDIR=/usr/local/X11/lib/X11/app-defaults:/usr/openwin/lib/app-defaults:/usr/lib/X11/app-defaults:/usr/local/X11R4/lib/X11/app-defaults

if [ ! "$TERM" ]; then
    TERM=vt100
fi

case $TERM in 
    xterms | xterm | tvi950 )
    ;;
    dialup )
# Your terminal type at home goes here    
#       setenv TERM tvi950
    ;;
    * )    
        TERM=vt100
        echo -n "Terminal type? ($TERM) "
        if [ ! "$DT" ]; then
                read newterm
                if  [ x$newterm != x ]; then
                    TERM=$newterm
                fi
        fi
esac

EDITOR=emacs
VISUAL=emacs
LESS=eM
MAILPATH=/usr/spool/mail/$USER:/var/mail/$USER

# Place your aliases here.
alias back="cd -"
alias ll="ls -lgs"
alias h="history 23"
alias j="jobs -l"
alias mak="make -k 2>&1 > ERRS &"
alias motd="/bin/cat /etc/motd"
alias rmt="rm *~ .*~"
alias lo="logout"
alias logo="logout"

# Place your functions here.
function dir { ls -Flagsq $@ | more ; }
function here { /usr/ucb/ps -aux | grep $@ | more ; }
function viewman { nroff -man $@ | less ; }


export PATH MANPATH TERM EDITOR VISUAL PS1 PGPPATH XAPPLRESDIR 
export PAGER LESS WHOCMD ARCH
