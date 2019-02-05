#include "sequencer.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/cache.hpp"
#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/log_manager.hpp"
#include "services/state_manager.hpp"

namespace otto::engines {

    using namespace ui;
    using namespace ui::vg;

    using Channel = Sequencer::Channel;

    int _samples_per_beat = 22050 / 4;
    int _counter = _samples_per_beat;
    bool _should_run = false;

};
