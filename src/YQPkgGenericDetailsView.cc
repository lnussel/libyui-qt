/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:	      YQPkgGenericDetailsView.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/

#define y2log_component "qt-pkg"
#include <ycp/y2log.h>
#include <qtabwidget.h>

#include "YQPkgGenericDetailsView.h"
#include "YQi18n.h"
#include "utf8.h"


YQPkgGenericDetailsView::YQPkgGenericDetailsView( QWidget * parent )
    : QTextBrowser( parent )
{
    _pkg = 0;
    _parentTab = dynamic_cast<QTabWidget *> (parent);
    
    if ( _parentTab )
    {
	connect( parent, SIGNAL( currentChanged( QWidget * ) ),
		 this,   SLOT  ( reload        ( QWidget * ) ) );
    }
}


YQPkgGenericDetailsView::~YQPkgGenericDetailsView()
{
    // NOP
}


void
YQPkgGenericDetailsView::reload( QWidget * newCurrent )
{
    if ( newCurrent == this )
    {
	showPkgDetailsIfVisible( _pkg );
    }
}


void
YQPkgGenericDetailsView::showPkgDetailsIfVisible( PMPackagePtr pkg )
{
    _pkg = pkg;
    
    if ( ! _parentTab )		// Is this view embedded into a tab widget?
    {
	if ( _parentTab->currentPage() == this )  // Is this page the topmost?
	{
	    showPkgDetails( pkg );
	}
    }
    else	// No tab parent - simply show data unconditionally.
    {
	showPkgDetails( pkg );
    }
}


QString
YQPkgGenericDetailsView::htmlHeading( PMPackagePtr pkg )
{
    QString html_text =
	"<table bgcolor=#E0E0F8><tr><td><b>"
	+ fromUTF8( pkg->name()     ) + "</b> - "
	+ fromUTF8( _pkg->summary() )
	+ "</td></tr></table><br>";
    
    return html_text;
}



#include "YQPkgGenericDetailsView.moc.cc"