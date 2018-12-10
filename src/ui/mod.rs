pub mod ui_type;

/* UI variants */
mod dialog;
mod cli;

use crate::settings::Settings;
use crate::user::User;
use ui::ui_type::UIType;

/**
 * Start the configured user interface.
 */
pub fn start(settings: &Settings) -> User {
    match settings.get_ui() {
        UIType::CLI => cli::start(settings),
        UIType::TUI => dialog::start(settings),
    }
}

