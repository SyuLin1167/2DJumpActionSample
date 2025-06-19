#include <thread>
#include "Loading.h"

namespace task
{
    Loading::Loading()
        : progress()
        , isLoading()
    {
        //�����Ȃ�
    }

    Loading::~Loading()
    {
        //�����Ȃ�
    }

    void Loading::AddTask(Level _level, std::function<void()> _task)
    {
        //�^�X�N�����Z
        taskInfo[Level::END].totalTasks++;
        taskInfo[_level].totalTasks++;

        //�^�X�N��ǉ�����
        taskInfo[_level].tasks.emplace_back(std::async(std::launch::async, [this, _level, _task]() {
            auto& info = taskInfo[_level];
            //DATA���x���ȊO�͑O�̃��x���̃^�X�N���I���܂ő҂�
            if (_level != Level::DATA)
            {
                taskInfo[static_cast<Level>(static_cast<int>(_level) - 1)].future.wait();
            }

            //�^�X�N���s
            _task();

            //�^�X�N�I���㏈��
            taskInfo[Level::END].finishTasks++;
            if (++info.finishTasks == info.totalTasks)
            {
                info.promise.set_value();
            }
        }));
    }

    void Loading::WatchProgress()
    {
        taskInfo[Level::END].tasks.emplace_back(std::async(std::launch::async, [this]() {
            auto& info = taskInfo[Level::END];
            //�S�^�X�N�I���܂Ń��[�v
            while (info.finishTasks < info.totalTasks)
            {
                progress = static_cast<float>(info.finishTasks) / info.totalTasks;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            progress = 1.0f;
            isLoading = false;
        }));
    }
}
