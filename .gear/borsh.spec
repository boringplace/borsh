# --no-sisyphus-check-out=fhs

%define peopledir shelter
%define reguser register

Name: borsh
Version: 0.0.1
Release: alt1

Summary: Boring server engine
License: GPLv3+
Group: System/Servers
Packager: Evgeny Sinelnikov <sin@altlinux.org>

Source: %name-%version.tar

Requires(pre): shadow-utils

%description
This package contains server engine initially developed for git.alt,
including administration and user utilities, git hooks, email
subscription support and config files.

%prep
%setup

%build
./autogen.sh
%configure \
	--with-peopledir=/%peopledir \
	--with-registerusername=%reguser
%make_build

%install
%makeinstall_std
mkdir -p %buildroot/%peopledir

%pre
%_sbindir/useradd -r %reguser -G users -d /var/empty -s /bin/borsh -c 'Borsh system registrator' ||:

%files
%doc COPYING AUTHORS
%attr(711,root,root) %_bindir/borsh
%dir %attr(755,root,root) /%peopledir/
%_man1dir/*

%changelog
* Wed May 02 2018 Evgeny Sinelnikov <sin@altlinux.org> 0.0.1-alt1
- Initial release for Sisyphus
