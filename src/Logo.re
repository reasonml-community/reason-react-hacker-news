open Utils;

let component = ReasonReact.statelessComponent("Logo");
let make = (~width, ~height, _children) => {
  {
    ...component,
    render: (_self) =>
      <svg width={width} height={height} viewBox="0 0 3925 3525">
        <circle stroke="none" fill="#fff" cx="1960" cy="1760" r="355"></circle>
        <g stroke="#fff" strokeWidth="170" fill="none">
          <ellipse cx="2575" cy="545" rx="715" ry="1875" transform="rotate(30)"></ellipse>
          <ellipse cx="1760" cy="-1960" rx="715" ry="1875" transform="rotate(90)"></ellipse>
          <ellipse cx="-815" cy="-2505" rx="715" ry="1875" transform="rotate(-210)"></ellipse>
        </g>
      </svg>
  }
}
