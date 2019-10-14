#-----------------------------------------------------------------------
set path=( ~/bin /usr/local/bin /usr/bin /bin /usr/openwin/bin /usr/dt/bin \
	/usr/local/X11/bin /usr/dt/bin /usr/ccs/bin /usr/ucb .)
umask 077
# so rsh works properly.  Note: lines below are executed only for
# an interactive shell.
if ( ! $?prompt ) exit
#
# GNU emacs users should have below line
setenv EDITOR emacs
#
# Set up the MANPATH environmental variable if on Solaris
if ( `uname` == "SunOS") then
  setenv MANPATH /usr/local/man:/usr/man:/usr/openwin/man:/usr/dt/man:/usr/local/X11/man:/opt/SUNWspro/man:/usr/dt/man:/usr/local/perl-module/man:/usr/share/local/ucbman
endif
#
# Tell the GUI where application defaults directory is located
setenv XAPPLRESDIR /usr/local/X11/lib/X11/app-defaults:/usr/openwin/lib/app-defaults:/usr/lib/X11/app-defaults:/usr/local/X11R4/lib/X11/app-defaults
#
# Place your aliases here.
alias back 'set tempwd=$oldwd;cd $tempwd; unset tempwd'
alias dir 'ls -alsFqg \!* | more'
alias ll ls -lgs
alias h 'history 23'
alias j jobs -l
alias mak 'make -k \!* >& ERRS &'
alias motd '/bin/cat /etc/motd'
alias term	 'set nonomatch; eval `tset -s -Q \!*`; unset nonomatch'
#
set cdpath=(~)
set notify=on
set history=200
set noclobber
if ( $?tcsh ) then
    alias cd 'set oldwd=$cwd;chdir \!*; set prompt="%m% "'
    alias po 'popd \!*; set prompt="%m% "'
    alias pu 'pushd \!*; set prompt="%m% "'
    if (  $?prompt ) set prompt="%m% "
    bindkey ^w backward-delete-word
    unset autologout
#   for tcsh within emacs    
    if $?EMACS unset edit
else
    set lochost = `hostname | awk -F. '{print $1}'`
    alias cd 'cd \!*; set prompt="$lochost% "'
    alias po 'popd \!*; set prompt="$lochost% "'
    alias pu 'pushd \!*; set prompt="$lochost% "'
    if (  $?prompt ) set prompt="$lochost% "
endif    
#
# If you want to get fancy with your prompt, you could try incorporating 
# the following set prompt commands in the above if-else-endif statement:
#
#     In the "if" part, replace the old set prompt commands with:
#
#		set prompt="[%m] %~ %! >"    
#
#  In the "else" part, replace the old set prompt commands with:
#
#		set prompt="[$lochost]: $cwd > "
#  
# For more information on modifying your shell environment, refer to the 
# man pages on csh, tcsh, and/or sh.
#
