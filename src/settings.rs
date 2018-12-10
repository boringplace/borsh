extern crate gettext;
extern crate yaml_rust;

use std::fs;
use std::fs::File;
use std::collections::HashMap;
use std::vec::Vec;
use std::io::{ Error, ErrorKind };
use self::gettext::Catalog;
use self::yaml_rust::YamlLoader;

use ui::ui_type::UIType;
use storage::StorageSettings;
use storage::storage_type::StorageType;
use verificator::method::AuthMethod;

fn load_storage_settings(config: &str) -> Result<StorageSettings, Error> {
    let cfg : String = fs::read_to_string(config)
        .expect("Unable to read configuration file");
    let yaml_doc = YamlLoader::load_from_str(&cfg).unwrap();
    let doc = &yaml_doc[0];

    /* Check if the necessary section is present in configuration
     * file. */
    if doc["storage"].is_badvalue() {
        return Err(Error::new(ErrorKind::Other,
            "No storage configured."));
    }

    /* Check the storage type is configured */
    if doc["storage"]["type"].is_badvalue() {
        return Err(Error::new(ErrorKind::Other,
            "No storage type configured."));
    }

    let mut configured_storage: StorageType;
    match doc["storage"]["type"].as_str().unwrap() {
        "sqlite" => {
            configured_storage = StorageType::SQLite;
        }
        _ => {
            return Err(Error::new(ErrorKind::Other,
                "Unknown storage type configured."));
        }
    }

    match configured_storage {
        StorageType::SQLite => {
            if !doc["storage"]["path"].is_badvalue() {
                return Ok(StorageSettings::new_local(configured_storage,
                    doc["storage"]["path"].as_str().unwrap()));
            } else {
                return Err(Error::new(ErrorKind::Other,
                    "SQLite3 storage path not configured."));
            }
        },
    }
}

fn load_checks(config: &str) -> Result<HashMap<AuthMethod, String>, Error> {
    let cfg : String = fs::read_to_string(config)
        .expect("Unable to read configuration file");
    let yaml_doc = YamlLoader::load_from_str(&cfg).unwrap();
    let doc = &yaml_doc[0];

    let mut checks: HashMap<AuthMethod, String>  = HashMap::new();

    if doc["checks"].is_badvalue() {
        return Err(Error::new(ErrorKind::Other,
            "Checks are not configured."));
    }

    if !doc["checks"]["email_script"].is_badvalue() {
        checks.insert(AuthMethod::Email,
            doc["checks"]["email_script"]
                .as_str()
                .unwrap()
                .to_string());
        println!("E-mail authentication configured.");
    }
    if !doc["checks"]["sms_script"].is_badvalue() {
        checks.insert(AuthMethod::SMS,
            doc["checks"]["sms_script"]
                .as_str()
                .unwrap()
                .to_string());
        println!("SMS authentication configured");
    }

    if checks.len() == 0 {
        return Err(Error::new(ErrorKind::Other,
            "No checks added to the configuration."));
    }

    return Ok(checks);
}

/**
 * Try to load the message catalog from the specified path or die.
 */
fn load_msgcat(catalog_path: &str) -> Catalog {
    let mcfile : File = File::open("ru.mo")
        .expect("could not open the catalog");
    let catalog : Catalog = Catalog::parse(mcfile)
        .expect("could not parse the catalog");
    return catalog;
}

/**
 * Default application language setting. The list is representing
 * languages existing as a message catalogs.
 */
enum Language {
    En,
    Ru,
}

/**
 * Program-wide objects.
 */
pub struct Settings {
    language: Language,
    msgcat: Option<Catalog>,
    ui: UIType,
    storage: StorageSettings,
    auth_methods: HashMap<AuthMethod, String>,
}

/**
 * Global application settings.
 */
impl Settings {
    /**
     * Settings loader-initializer. Tries to load settings from
     * anywhere (from a YAML file as for now) or initialize the
     * application with some sensible defaults.
     */
    pub fn new(config: &str) -> Self {
        let cfg : String = fs::read_to_string(config)
            .expect("Unable to read configuration file");
        let yaml_doc = YamlLoader::load_from_str(&cfg).unwrap();
        let doc = &yaml_doc[0];

        let mut setting : Settings = Settings { msgcat: None,
            ui: UIType::TUI,
            language: Language::En,
            storage: load_storage_settings(config).unwrap(),
            auth_methods: load_checks(config).unwrap(), };

        if !doc["borsh"].is_badvalue() {
            if !doc["borsh"]["lang"].is_badvalue() {
                match doc["borsh"]["lang"].as_str().unwrap() {
                    "ru" => {
                        setting.msgcat = Some(load_msgcat("ru.mo"));
                        setting.language = Language::Ru;
                        println!("Default language configured to Russian.");
                        println!("Loading ru.mo message catalog");
                    },
                    _ => {
                        setting.msgcat = None;
                        println!("Erroneously configured language setting.");
                    },
                }
            } else {
                println!("No language setting found! Using default value of English UI.");
            }

            if !doc["borsh"]["ui"].is_badvalue() {
                match doc["borsh"]["ui"].as_str().unwrap() {
                    "tui" => {
                        setting.ui = UIType::TUI;
                    },
                    "cli" => {
                        setting.ui = UIType::CLI;
                    },
                    _ => {
                        setting.ui = UIType::TUI;
                    }
                }
            } else {
                setting.ui = UIType::TUI;
            }
        }

        return setting;
    }

    /**
     * Translate the given string according to the loaded message
     * catalog.
     */
    pub fn tr(&self, text: &str) -> String {
        match &self.msgcat {
            None => String::from(text),
            Some(cat) => String::from(cat.gettext(text)),
        }
    }

    /**
     * Get the configured UI ID.
     */
    pub fn get_ui(&self) -> &UIType {
        return &self.ui;
    }

    /**
     * Get the backend handler.
     */
    pub fn get_storage_settings(&self) -> &StorageSettings {
        return &self.storage;
    }

    /**
     * Get the list of available authentication methods.
     */
    pub fn get_auth_methods(&self) -> Vec<AuthMethod> {
        let mut methods : Vec<AuthMethod> = Vec::new();
        for key in self.auth_methods.keys() {
            methods.push(*key);
        }
        return methods;
    }
}

