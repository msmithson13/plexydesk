/*****************************************************************
This file is part of the KDE project.

Copyright (C) 2003 Lubos Lunak <l.lunak@kde.org>

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
******************************************************************/

#include "kdecorationfactory.h"

#include <assert.h>

#include "kdecorationbridge.h"

KDecorationFactory::KDecorationFactory()
    {
    }
    
KDecorationFactory::~KDecorationFactory()
    {
    assert( _decorations.count() == 0 );
    }

bool KDecorationFactory::reset( unsigned long )
    {
    return true;
    }
    
void KDecorationFactory::checkRequirements( KDecorationProvides* )
    {
    }

QList< KDecorationDefines::BorderSize > KDecorationFactory::borderSizes() const
    {
    return QList< BorderSize >() << BorderNormal;
    }
    
bool KDecorationFactory::exists( const KDecoration* deco ) const
    {
    return _decorations.contains( const_cast< KDecoration* >( deco ));
    }
    
void KDecorationFactory::addDecoration( KDecoration* deco )
    {
    _decorations.append( deco );
    }
    
void KDecorationFactory::removeDecoration( KDecoration* deco )
    {
    _decorations.removeAll( deco );
    }

void KDecorationFactory::resetDecorations( unsigned long changed )
    {
    for( QList< KDecoration* >::ConstIterator it = _decorations.begin();
         it != _decorations.end();
         ++it )
        (*it)->reset( changed );
    }

NET::WindowType KDecorationFactory::windowType( unsigned long supported_types, KDecorationBridge* bridge ) const
    {
    return bridge->windowType( supported_types );
    }

QList< QList<QImage> > KDecorationFactoryUnstable::shadowTextures()
    {
    return QList< QList<QImage> >();
    }

int KDecorationFactoryUnstable::shadowTextureList( ShadowType type ) const
    {
    Q_UNUSED( type );
    return -1;
    }

QList<QRect> KDecorationFactoryUnstable::shadowQuads( ShadowType type, QSize size ) const
    {
    Q_UNUSED( type );
    Q_UNUSED( size );
    return QList<QRect>();
    }

double KDecorationFactoryUnstable::shadowOpacity( ShadowType type ) const
    {
    Q_UNUSED( type );
    return 1.0;
    }

double KDecorationFactoryUnstable::shadowBrightness( ShadowType type ) const
    {
    Q_UNUSED( type );
    return 1.0;
    }

double KDecorationFactoryUnstable::shadowSaturation( ShadowType type ) const
    {
    Q_UNUSED( type );
    return 1.0;
    }