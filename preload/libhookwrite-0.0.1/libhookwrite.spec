Summary:	libhookwrite -- check write(2) system call
Name:		libhookwrite
Version:	0.0.1
Release:	1
License:	LGPL
Group:		System Environment/Libraries
Packager:	Masato BITO <masato@bz2.jp>
URL:		http://bz2.jp/
Source:		%{name}-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-root

%description
libhookwrite is used to check write(2) and update mtime of a specified file. libhookwrite is supporsed to call by setting LD_PRELOAD environment variable for overwriting write(2) system call. When write(2) is called libhookwrite updates mtime of a file which is indecated by CHKWRITE_UPDATE_FILE.
ex:
HOOKWRITE_UPDATE_FILE=$HOME/chkupdate LD_PRELOAD=/usr/lib/libhookwrite.so vim test.txt

%prep
%setup -q
%configure

%build
make

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_libdir}/*
%doc AUTHORS COPYING ChangeLog INSTALL NEWS README

%changelog
* Sun Jul 30 2006 Masato BITO <masato@bz2.jp>
- first release
