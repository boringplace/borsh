use settings::Settings;
use user::User;

use ui;
use ui::ui_type::UIType;
use verificator;
use storage;
use storage::StorageBackend;
use storage::storage_type::StorageType;

/**
 * Global application data.
 */
pub struct Runner {
    settings: Settings,
    storage:  Box<StorageBackend>,
}

/**
 * C++-alike class encapsulating application state.
 */
impl Runner {
    /**
     * Initialize the application's message catalogs, loggers,
     * database connections, etc.
     */
    pub fn new() -> Self {
        let stn : Settings = Settings::new("/var/borsh/config.yml");
        match stn.get_ui() {
            UIType::CLI => {
                println!("{}", stn.tr("BoringShell UI configured to CLI."));
            },
            UIType::TUI => {
                println!("{}", stn.tr("BoringShell UI configured to TUI."));
            },
        }
        match stn.get_storage_settings().get_storage_type() {
            StorageType::SQLite => {
                println!("{}", stn.tr("BoringShell storage configured to SQLite."));
            },
        }
        let backend : Box<StorageBackend> = storage::get(stn.get_storage_settings());

        let app : Runner = Runner { settings: stn,
            storage: backend };

        return app;
    }

    /**
     * Run the user registration UI:
     *
     * # Description
     *
     * - Start the interface for getting the information from the
     *   user.
     * - Get the structure representing the new user.
     * - Add the user to the database.
     * - Start the interface for user verification.
     * - Get the structure representing updated user state.
     * - Update the user state in the database.
     * - Exit the shell.
     */
    pub fn run(&self) {
        println!("{}", self.settings.tr("BoringHub registration"));
        let registrant : User = ui::start(&self.settings);
        println!("{}: {}", self.settings.tr("User added"), &registrant.name());
        let checked : bool = verificator::check(&registrant);
        if checked {
            println!("{}", self.settings.tr("User is verified."));
        } else {
            println!("{}", self.settings.tr("User is not verified."));
        }
    }
}

