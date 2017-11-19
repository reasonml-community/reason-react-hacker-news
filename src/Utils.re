/* require css file for side effect only */
[@bs.val] external requireCSS : string => unit = "require";

/* require an asset (eg. an image) and return exported string value (image URI) */
[@bs.val] external requireAssetURI : string => string = "require";

[@bs.val] external currentTime : unit => int = "Date.now";

/* format a timestamp in seconds as relative humanised time sentence */
let fromNow = (unixtime) => {
  let delta = currentTime() / 1000 - unixtime;
  if (delta < 3600) {
    string_of_int(delta / 60) ++ " minutes ago"
  } else if (delta < 86400) {
    string_of_int(delta / 3600) ++ " hours ago"
  } else {
    string_of_int(delta / 86400) ++ " days ago"
  }
};

[@bs.send] external internal_getAttribute : (Js.t('a), string) => Js.null(string) = "getAttribute";

let getAttribute = (node, name) => Js.Null.to_opt(internal_getAttribute(node, name));

[@bs.module "src/UtilsJS"] external dangerousHtml : string => Js.t('a) = "dangerousHtml";

[@bs.module "src/UtilsJS"] external distanceFromBottom : unit => int = "distanceFromBottom";

[@bs.module "src/UtilsJS"] external registerServiceWorker : unit => unit = "registerServiceWorker";

let intEl = (n) => ReasonReact.stringToElement(string_of_int(n));

let textEl = (str) => ReasonReact.stringToElement(str);
