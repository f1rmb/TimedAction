/*
  Copyright (C) 2013 F1RMB, Daniel Caujolle-Bert <f1rmb.daniel@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "TimedAction.h"

#if USE_MUTEX
#include "Mutex.cpp"
#define LOCK   do { m_mutex.lock(); } while(0)
#define UNLOCK do { m_mutex.unlock(); } while(0)
#else
#define LOCK   do { } while(0)
#define UNLOCK do { } while(0)
#endif

/*
|| <<constructor>>
*/
TimedAction::TimedAction(unsigned long interval, callback_t callback, void *data, boolean enable)
{
    _create(0, interval, callback, data, enable);
}

/*
|| <<constructor>>
*/
TimedAction::TimedAction(unsigned long previous, unsigned long interval, callback_t callback, void *data, boolean enable)
{
    _create(previous, interval, callback, data, enable);
}

void TimedAction::_create(unsigned long previous, unsigned long interval, callback_t callback, void *data, boolean enable)
{
    m_enabled  = enable;
	m_previous = previous;
	m_interval = interval;
    m_callback = callback;
    m_data     = data;
}

void TimedAction::reset()
{
    LOCK;
    m_previous = millis();
    UNLOCK;
}

boolean TimedAction::disable()
{
    return (enable(false));
}

boolean TimedAction::enable(boolean enable)
{
    bool ret = false;

    LOCK;
    if (enable != m_enabled)
    {
        if ((m_enabled = enable) == true)
            m_previous = millis();

        ret = true;
    }
    UNLOCK;

    return ret;
}

boolean TimedAction::isEnabled()
{
    boolean ret;

    LOCK;
    ret = m_enabled;
    UNLOCK;

    return ret;
}

boolean TimedAction::check()
{
    boolean ret = false;

    LOCK;
    if ((m_enabled == true) && ((millis() - m_previous) >= m_interval))
    {
        m_previous = millis();
        m_callback(m_data);
        ret = true;
    }
    UNLOCK;

    return ret;
}

void TimedAction::setInterval(unsigned long interval)
{
    LOCK;
    m_interval = interval;
    UNLOCK;
}

unsigned long TimedAction::getInterval()
{
    unsigned long v;

    LOCK;
    v = m_interval;
    UNLOCK;

    return v;
}

void TimedAction::setData(void *data)
{
    LOCK;
    m_data = data;
    UNLOCK;
}
