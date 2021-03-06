// Copyright (c) 2013-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "webosshell.h"
#include "webosshell_p.h"
#include "webosshellsurface.h"
#include "webosshellsurface_p.h"

#include <QtWaylandClient/private/qwaylanddisplay_p.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>
#include <QWindow>
#include <QDebug>

static bool platformWindowCreated(QWindow* w)
{
    Q_ASSERT(w);
    bool created = w->handle();
    if (!created) {
        qWarning() << "QPlatformWindow not available for window" << w;
        qWarning() << "Please make the window visible atleast once before aquiring";
        qWarning() << "webOS platform resources";
    }
    return created;
}

WebOSShellPrivate::WebOSShellPrivate(QWaylandDisplay* display, uint32_t id)
    : m_display(display)
{
    m_shell = static_cast<wl_webos_shell*>(wl_registry_bind(display->wl_registry(), id, &wl_webos_shell_interface, 1));
}

WebOSShellPrivate::~WebOSShellPrivate()
{
}

QWaylandShellSurface* WebOSShellPrivate::createShellSurface(QPlatformWindow* window)
{
    QWaylandWindow* waylandWindow = static_cast<QWaylandWindow*>(window);
    struct wl_webos_shell_surface* webos_shell_surface = wl_webos_shell_get_shell_surface(m_shell, waylandWindow->object());
    struct wl_shell_surface *shell_surface = 0;

    // QWaylandShell
    if (m_display->shell())
        shell_surface = m_display->shell()->get_shell_surface(waylandWindow->object());

    WebOSShellSurface *webosShellSurface = new WebOSShellSurface(webos_shell_surface, shell_surface, window);

    return WebOSShellSurfacePrivate::get(webosShellSurface);
}

WebOSShell::WebOSShell(QWaylandDisplay* display, uint32_t id)
    : d_ptr(new WebOSShellPrivate(display, id))
{
}

WebOSShell::~WebOSShell()
{
}

WebOSShellSurface* WebOSShell::shellSurfaceFor(QWindow* window)
{
    WebOSShellSurfacePrivate* ssp = NULL;
    if (platformWindowCreated(window)) {
        QWaylandWindow* qww = static_cast<QWaylandWindow*>(window->handle());
        ssp = static_cast<WebOSShellSurfacePrivate *>(qww->shellSurface());
    }
    return ssp ? ssp->shellSurface() : NULL;
}
