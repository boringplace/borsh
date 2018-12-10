extern crate cursive;

pub use self::cursive::Cursive;
pub use self::cursive::views::{Dialog, TextView};

use crate::user::User;
use crate::settings::Settings;

pub fn start(settings: &Settings) -> User {
    let whead  : &str = r#"BoringHub registration"#;
    let wgreet : &str = r#"BoringHub user registration"#;

    let mut croot = Cursive::default();

    croot.add_layer(Dialog::around(TextView::new(settings.tr(whead)))
        .title(settings.tr(wgreet))
        .button(settings.tr("Quit"), |s| s.quit()));

    croot.run();
    let new_user : User = User::new("Igor Chudov".to_string());
    return new_user;
}

