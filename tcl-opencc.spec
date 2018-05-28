%{!?directory:%define directory /usr}

%define buildroot %{_tmppath}/%{name}
%define pkgname tclopencc

Name:          tcl-opencc
Summary:       Tcl bindings for OpenCC (libopencc)
Version:       0.1
Release:       0
License:       Apache License 2.0
Group:         Development/Libraries/Tcl
Source:        %{name}-%{version}.tar.gz
URL:           https://github.com/ray2501/tcl-opoencc
BuildRequires: autoconf
BuildRequires: make
BuildRequires: gcc
BuildRequires: pkg-config
BuildRequires: tcl-devel >= 8.4
BuildRequires: opencc-devel >= 1.0.0
Requires:      tcl >= 8.4
BuildRoot:     %{buildroot}

%description
OpenCC is an opensource project for conversion between Traditional 
Chinese and Simplified Chinese, supporting character-level conversion, 
phrase-level conversion, variant conversion and regional idioms among 
Mainland China, Taiwan and Hong kong.

tcl-opencc is Tcl bindings for OpenCC (libopencc).

%prep
%setup -q -n %{name}-%{version}

%build
./configure \
	--prefix=%{directory} \
	--exec-prefix=%{directory} \
	--libdir=%{directory}/%{_lib}
make 

%install
make DESTDIR=%{buildroot} pkglibdir=%{tcl_archdir}/%{pkgname}%{version} install

%clean
rm -rf %buildroot

%files
%defattr(-,root,root)
%{tcl_archdir}

