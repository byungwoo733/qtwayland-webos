// Copyright (c) 2015-2018 LG Electronics, Inc.
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

#ifndef WEBOSSHELLINTEGRATION_H
#define WEBOSSHELLINTEGRATION_H

#include <QtWaylandClient/private/qwaylandshellintegration_p.h>

QT_BEGIN_NAMESPACE

class WebOSShell;

class WebOSShellIntegration : public QWaylandShellIntegration
{
public:
    WebOSShellIntegration();
    virtual ~WebOSShellIntegration();

    bool initialize(QWaylandDisplay *display);
    QWaylandShellSurface *createShellSurface(QWaylandWindow *window);
    QWaylandDisplay *display() { return m_display; }

    static void registry_global(void *data, struct wl_registry *registry, uint32_t id, const QString &interface, uint32_t version);

private:
    QWaylandDisplay *m_display;
};

QT_END_NAMESPACE

#endif // WEBOSSHELLINTEGRATION_H
