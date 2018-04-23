/* require css file for side effect only */
[@bs.val] external requireCSS : string => unit = "require";
/* require css module file */
[@bs.val] external requireCSSModule : string => Js_dict.t(string) = "require";
/* get class name out of css modules object */
let className = (styles, key) => Js_dict.unsafeGet(styles, key);
/* get class names based on filter and concatenate into single string */
let classNameFilter = (styles, classes) =>
  Array.fold_left((curr, next) => {
    let (className, predicate) = next;
    if (!predicate) {
      curr
    } else {
      switch (Js_dict.get(styles, className)) {
        | None => curr /* ignoring error */
        | Some(value) => curr ++ " " ++ value
      }
    }
  }, "", classes);

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

[@bs.send] [@bs.return nullable] external getAttribute : (Js.t('a), string) => option(string) = "getAttribute";

let dangerousHtml : string => Js.t('a) = html => {
  "__html": html
};

let distanceFromBottom : unit => int = () => {
  let bodyClientHeight = [%raw "document.body.clientHeight"];
  let windowScrollY = [%raw "window.scrollY"];
  let windowInnerHeight = [%raw "window.innerHeight"];
  bodyClientHeight - (windowScrollY + windowInnerHeight)
};

[@bs.module] external registerServiceWorker : unit => unit = "src/registerServiceWorker";

let intEl = (n) =>
  n |> string_of_int
    |> ReasonReact.stringToElement;

let textEl = ReasonReact.stringToElement;
let arrayEl = ReasonReact.arrayToElement;
