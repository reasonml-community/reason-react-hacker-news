let component = ReasonReact.statelessComponent("Link");

let handleClick = (href, event) =>
  if (!ReactEvent.Mouse.defaultPrevented(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReact.Router.push(href);
  };

let make = (~href, ~className="", children) => {
  ...component,
  render: _self =>
    ReasonReact.createDomElement(
      "a",
      ~props={
        "href": href,
        "className": className,
        "onClick": handleClick(href),
      },
      children,
    ),
};
