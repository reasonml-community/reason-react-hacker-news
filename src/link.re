let handleClick = href => ReasonReactRouter.push(href);

[@react.component]
let make = (~href, ~className="", ~children) =>
  <a href className onClick={_event => handleClick(href)}> children </a>;
