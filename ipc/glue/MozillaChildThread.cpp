/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: sw=2 ts=8 et :
 */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Plugin App.
 *
 * The Initial Developer of the Original Code is
 *   Ben Turner <bent.mozilla@gmail.com>.
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "mozilla/ipc/MozillaChildThread.h"

#include "nsXPCOM.h"

#ifdef XP_WIN
#include <objbase.h>
#endif

namespace mozilla {
namespace ipc {

void
MozillaChildThread::OnControlMessageReceived(const IPC::Message& aMessage) {
  /*
  IPC_BEGIN_MESSAGE_MAP(MozillaChildThread, aMessage)
  IPC_END_MESSAGE_MAP()
  */
}

void
MozillaChildThread::Init()
{
  ChildThread::Init();

#ifdef XP_WIN
  // Silverlight depends on the host calling CoInitialize.
  ::CoInitialize(NULL);
#endif
  // Add notification service here once bug 560630 is fixed

  // Certain plugins, such as flash, steal the unhandled exception filter
  // thus we never get crash reports when they fault. This call fixes it.
  message_loop()->set_exception_restoration(true);

  NS_LogInit();
}

void
MozillaChildThread::CleanUp()
{
  NS_LogTerm();

#ifdef XP_WIN
  ::CoUninitialize();
#endif
}

} // namespace ipc
} // namespace mozilla