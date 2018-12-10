use std::io::{ self, Write, BufRead, Error, ErrorKind };
use rand;

use crate::user::User;
use crate::settings::Settings;
use crate::verificator::method::AuthMethod;

/**
 * Print some translated guesture for user input.
 */
fn guesture(settings: &Settings, guesture: &str) {
    print!("{}", settings.tr(guesture));
    io::stdout().flush().unwrap();
}

/**
 * Ask user's login.
 */
fn get_login(settings: &Settings) -> String {
    let stdin = io::stdin();
    let mut input_iterator = stdin.lock().lines();

    guesture(settings,
        "Your new login (ASCII, without whitespaces, will be converted to lowercase): ");
    let login = input_iterator.next().unwrap().unwrap();
    return login;
}

/**
 * Suggest an authorization method for a user.
 */
fn get_amethod(settings: &Settings) -> AuthMethod {
    let stdin = io::stdin();
    let mut input_iterator = stdin.lock().lines();

    guesture(settings,
        "Choose authentication method: ");
    let auth_method = input_iterator.next().unwrap().unwrap();

    let method : Result<AuthMethod, Error> = AuthMethod::decode_method(auth_method);

    match method {
        Ok(amethod) => {
            match amethod {
                AuthMethod::Email => {
                    println!("email selected");
                    return amethod;
                },
                AuthMethod::SMS => {
                    println!("sms selected");
                    return amethod;
                },
            }
        },
        Err(err) => {
            return AuthMethod::SMS;
        }
    }
}

pub fn start(settings: &Settings) -> User {
    let login = get_login(settings);
    let mut new_user : User = User::new(login);
    let auth_method : AuthMethod = get_amethod(settings);
    new_user.update_auth_method(auth_method);

    /* u16 is random enough and also easy enough so users less likely
     * make a mistake */
    let authn : u16 = rand::random::<u16>();

    return new_user;
}

