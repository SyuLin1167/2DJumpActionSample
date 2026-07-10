module Collider;

namespace col2d
{
    void Collider::TriggerEvent(const uint64_t& key)
    {
        // イベントが存在しなければ実施しない
        if (m_events.find(key) == m_events.end())
        {
            return;
        }

        // 条件を満たしていればイベントを実行
        for (auto& event : m_events[key])
        {
            if (!event.when || event.when())
            {
                event.event();
            }
        }
    }
}